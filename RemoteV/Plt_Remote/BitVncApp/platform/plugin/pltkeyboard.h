#ifndef PLTKEYBOARD_H
#define PLTKEYBOARD_H

#include <QWidget>
#include <QDialog>
#include <QKeyEvent>
#include <QPushButton>
namespace Ui {
class pltKeyBoard;
}

class pltKeyBoard : public QDialog
{
    Q_OBJECT
    #define SA_KEY_NUM 64

public:
    explicit pltKeyBoard(QWidget *parent = 0);
    ~pltKeyBoard();
    void init();
private slots:
    void btn_clicked();
    void on_pb_cancel_clicked();

private:
    QWidget *mParent;
    Ui::pltKeyBoard *ui;
    qint32 mCapLockOn,mCtrlFlag,mShiftFlag;
    QMap <QPushButton*,qint32> key_btn;
    void keyPressEvent(QKeyEvent *event);
    void initKeyBoard();
    void CapslockChange();
    void ShiftChange();
};
#endif // PLTKEYBOARD_H
