#ifndef SA_DIALOG_SPUREM_H
#define SA_DIALOG_SPUREM_H

#include <QWidget>
#include <QKeyEvent>
#include "sa_interface_dialog.h"
class SA_LineEdit;
class SA_Combobox;
class SA_Dialog_DigitInput;
class controlInterface;

namespace Ui {
class SA_Dialog_SpurEM;
}

class SA_Dialog_SpurEM : public QWidget,public sa_interface_dialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_SpurEM(controlInterface *interface,QWidget *parent = 0);
    ~SA_Dialog_SpurEM();
    void initDisplay(); //init display
    void initWidget();  // init control display and hide
    void showWidget();
    void hideWidget();
signals:
    void mDialogHide();
private:
    void keyPressEvent(QKeyEvent *event);
    void initMap();
    void showInputDialog(qint32 index);
    void refreshEdit(qint32 index);
    void refreshSubMenu(qint32 mTableType);
    qint32 RbwVbwCompare(qint32 value);
    void refreshCombobox();
    void getKnobValue(qint32 mode);
private slots:
    void on_finishEntry(qint32 index);
    void edit_clicked();
    void on_pb_cancel_clicked();

    void on_pb_RangePara_1_clicked(bool checked);

    void on_pb_RangePara_2_clicked(bool checked);

    void on_RBWBox_currentIndexChanged(int index);

    void on_VBWBox_currentIndexChanged(qint32 index);

    void on_pb_Ave_1_clicked(bool checked);

    void on_pb_Ave_2_clicked(bool checked);

    void on_pb_Report_Mode1_clicked(bool checked);

    void on_pb_Report_Mode2_clicked(bool checked);

    void on_pb_ReMeasure_clicked();

    void on_pb_RangeOn_clicked(bool checked);
    void on_getComboBoxFocus(SA_Combobox* mBox);
    void on_getFocus(SA_LineEdit* mEdit);
private:
    Ui::SA_Dialog_SpurEM *ui;
    controlInterface *mControl;
    qint32 mCurEdit;
    QMap <quint32,SA_LineEdit*> mEditList;
    QMap <quint32,SA_Combobox*> mBoxList;
    SA_Dialog_DigitInput* mInputDialog;
    qint32 tableType;
protected:
    void hide();
};

#endif // SA_DIALOG_SPUREM_H
