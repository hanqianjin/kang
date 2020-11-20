#ifndef SA_DIALOG_VIRTUALKEYBOARD_H
#define SA_DIALOG_VIRTUALKEYBOARD_H

#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
namespace Ui {
class SA_Dialog_VirtualKeyboard;
}

class SA_Dialog_VirtualKeyboard : public QWidget
{
    Q_OBJECT
    #define SA_KEY_NUM 64

public:
    explicit SA_Dialog_VirtualKeyboard(QWidget *parent = 0);
    ~SA_Dialog_VirtualKeyboard();
    void init();
private slots:
    void btn_clicked();
private:
    QWidget *mParent;
    Ui::SA_Dialog_VirtualKeyboard *ui;
    qint32 mCapLockOn,mCtrlFlag,mShiftFlag;
    QMap <QPushButton*,qint32> key_btn;
    void keyPressEvent(QKeyEvent *event);
    void initKeyBoard();
    void CapslockChange();
    void ShiftChange();
};

#endif // SA_DIALOG_VIRTUALKEYBOARD_H
