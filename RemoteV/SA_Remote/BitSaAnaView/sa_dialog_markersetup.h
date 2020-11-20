#ifndef SA_DIALOG_MARKERSETUP_H
#define SA_DIALOG_MARKERSETUP_H
#include <QPushButton>
#include <QWidget>
#include <QDialog>
#include <sa_lineedit.h>
#include <QDebug>
#include <QKeyEvent>
#include "define.h"
#include "sa_interface_dialog.h"

class SA_Dialog_DigitInput;
class controlInterface;
class user_variable;

namespace Ui {
class SA_Dialog_MarkerSetup;
}

class SA_Dialog_MarkerSetup : public QWidget,public sa_interface_dialog
{
    Q_OBJECT
public:
    explicit SA_Dialog_MarkerSetup(controlInterface *interface,user_variable *puser_variable,QWidget *parent = 0 );
    ~SA_Dialog_MarkerSetup();
    void refreshDisplay();
    void refreshMarkerEdit(qint32 index = -1);

    void initDisplay(); //init display
    void initWidget(); // init control display and hide
    void showWidget();
    void hideWidget();
signals:
    void mDialogHide();
private slots:
    void on_finishEntry(qint32 index);
    void mMarkerSelectGroup_click(qint32 index);
    void on_pb_toggle_clicked();
    void on_pb_cancel_clicked();
    void on_pb_Normal_clicked();
    void on_pb_Delta_clicked();
    void on_pb_DeltaPair_clicked();
    void on_pb_toggle_toggled(bool checked);
    void on_pb_MkrNoise_clicked();
    void on_pb_MkrNoise_toggled(bool checked);
    void on_pb_FreqCount_clicked();
    void on_pb_FreqCount_toggled(bool checked);
    void on_edit_MkrFreq_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_pb_Start_clicked();

    void on_pb_Center_clicked();

    void on_pb_Stop_clicked();

    void on_pb_MkrAllOn_clicked();

private:

    Ui::SA_Dialog_MarkerSetup *ui;
    SA_Dialog_DigitInput *mInputDialog;
    controlInterface *mControl;
    user_variable *globalUserVariable;
    QButtonGroup *mMarkerSelectGroup;
    void initMap();
    void showInputDialog(qint32 index);
    void editclicked(quint32 index = -1);
    void refreshMarkerType(qint32 markerIndex=-1);
    void refreshMarkerNoise();
    void markerSelect(qint32 index);
    void digitInputClose();
    void refreshMarker(qint32 index =-1);
};
#endif // SA_DIALOG_MARKERSETUP_H
