#ifndef PM_DIALOG_DISPLAYSETUP_H
#define PM_DIALOG_DISPLAYSETUP_H

#include <QWidget>
#include "pm_interface.h"
#include "pm_dialog_digitinput.h"
#include "pm_lineedit.h"
#include "pm_define.h"
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class Pm_Dialog_DisplaySetup;
}

class Pm_Dialog_DisplaySetup : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_DisplaySetup(BitPm_Interface *BitPmInterface = NULL, Pm_Dialog_Digitinput *input = NULL, QWidget *parent = 0);
    ~Pm_Dialog_DisplaySetup();
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void finishEntry_Display(qint32 index);
    void on_pb_cancel_clicked();
    void DigitalKeyRespond(QKeyEvent *event);
    void on_timeOut();

    void on_pb_sensorType_activated(int index);

    void on_pb_reverseDisplay_activated(int index);
    void on_pb_fowardDisplay_activated(int index);
    void on_pb_summary_clicked();
    void finishCmd_Display();

public:
    void initDisplay();
private:
    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);

private:
    Ui::Pm_Dialog_DisplaySetup *ui;
   BitPm_Interface *PmInterfaceObj;
    Pm_Dialog_Digitinput *mInputDialog;
    QMap <quint32,Pm_LineEdit*> mEditList;

    qint32 mSelectInputID;
    QTimer *timer;
    qint32 mUpDownFlag;
};

#endif // PM_DIALOG_DISPLAYSETUP_H
