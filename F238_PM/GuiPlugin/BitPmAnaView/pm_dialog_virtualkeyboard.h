#ifndef PM_DIALOG_VIRTUALKEYBOARD_H
#define PM_DIALOG_VIRTUALKEYBOARD_H

#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
namespace Ui {
class Pm_dialog_virtualkeyboard;
}

class Pm_dialog_virtualkeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_dialog_virtualkeyboard(QWidget *parent = 0);
    ~Pm_dialog_virtualkeyboard();
private slots:
    void btn_clicked();
private:
    QWidget *mParent;
    Ui::Pm_dialog_virtualkeyboard *ui;
    qint32 mCapLockOn,mCtrlFlag,mShiftFlag;
    QMap <QPushButton*,qint32> key_btn;
    void keyPressEvent(QKeyEvent *event);
    void initKeyBoard();
    void CapslockChange();
    void ShiftChange();
};

#endif // PM_DIALOG_VIRTUALKEYBOARD_H
