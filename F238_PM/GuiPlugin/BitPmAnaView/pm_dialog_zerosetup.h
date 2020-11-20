#ifndef PM_DIALOG_ZEROSETUP_H
#define PM_DIALOG_ZEROSETUP_H

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include "pm_interface.h"
#include "pm_dialog_digitinput.h"
#include <QKeyEvent>
#include <QTimer>
#include "pm_lineedit.h"
#include "pm_dialog_caltable.h"
#include "pm_user_variable.h"
#include "pm_dialog_warning.h"

namespace Ui {
class Pm_Dialog_ZeroSetup;
}

class Pm_Dialog_ZeroSetup : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_ZeroSetup(BitPm_Interface *BitPmInterface = NULL, Pm_Dialog_Digitinput *Input = NULL, QWidget *parent = 0);
    ~Pm_Dialog_ZeroSetup();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void finishEntry_zero(qint32 index);
    void on_pb_cancel_clicked();
    void DigitalKeyRespond(QKeyEvent* event);
    void on_timeOut();

    void on_pb_setZero_clicked();
    void on_pb_calFactor_clicked();

    void on_calDestroyed();


public:
    void initDisplay();
private:
    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);

private:
    Ui::Pm_Dialog_ZeroSetup *ui;
    BitPm_Interface *PmInterfaceObj;
    Pm_Dialog_Digitinput *mInputDialog;
    QMap <quint32,Pm_LineEdit*> mEditList;

    qint32 mSelectInputID;
    QTimer* timer;
    qint32 mUpDownFlag;
    Pm_Dialog_CalTable *mCalTable;
};

#endif // PM_DIALOG_ZEROSETUP_H
