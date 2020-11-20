#ifndef SA_DIALOG_FREQSETUP_H
#define SA_DIALOG_FREQSETUP_H
#include <sa_lineedit.h>
#include <QWidget>
#include <QDialog>
#include <QMap>
#include <QDebug>
#include <QKeyEvent>

#include "sa_interface_dialog.h"

class SA_Dialog_DigitInput;
class controlInterface;
class user_variable;
class SA_Dialog_CH_Std;
namespace Ui {
class SA_Dialog_FreqSetup;
}

class SA_Dialog_FreqSetup : public QWidget,public sa_interface_dialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_FreqSetup(controlInterface *interface, user_variable *puser_variable, QWidget *parent = 0 );
    ~SA_Dialog_FreqSetup();
    void initDisplay(); //init display
    void initWidget(); // init control display and hide
    void showWidget();
    void hideWidget();

    void refreshEditDisplay(quint32 index);
private slots:
    void on_finishEntry(qint32 index);
    void on_LedCenterFreq_clicked();
    void on_pb_FullSpan_clicked();
    void on_pb_ZeroSpan_clicked();
    void on_pb_LastSpan_clicked();
    void on_LedStartFreq_clicked();
    void on_LedStopFreq_clicked();
    void on_LedSpan_clicked();
    void on_LedFreqStep_clicked();
    void on_LedFreqOffset_clicked();
    void on_pb_cancel_clicked();
    void on_getFocus(SA_LineEdit* mEdit);
    void on_LedCHStandard_clicked();
    void on_LedCHNum_clicked();
    void on_LedCHStep_clicked();
    void on_pb_Uplink_clicked();
    void on_pb_Downlink_clicked();
    void on_CHStdClose();
protected slots:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::SA_Dialog_FreqSetup *ui;
    SA_Dialog_DigitInput *mInputDialog;
    SA_Dialog_CH_Std *mCHStdDialog;
    controlInterface *mControl;
    user_variable *globalUserVariable;
    QMap <quint32,SA_LineEdit*> mEditList;
    qint32 mCurEdit;
    QWidget* mParentWin;
    void initMap();
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    void digitInputClose();
    void showCHStdDialog();
    void getKnobValue(qint32 mode);
signals:
    void mDialogHide();
};
#endif // SA_DIALOG_FREQSETUP_H
