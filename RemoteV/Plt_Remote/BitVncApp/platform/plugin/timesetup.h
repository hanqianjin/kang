#ifndef TIMESETUP_H
#define TIMESETUP_H

#include <QDialog>

namespace Ui {
class timeSetup;
}

class timeSetup : public QDialog
{
    Q_OBJECT

public:
    explicit timeSetup(QWidget *parent = 0);
    ~timeSetup();
    qint32 exec();
private slots:
    void on_up_hour_clicked();
    void on_down_hour_clicked();
    void on_up_minu_clicked();
    void on_down_minu_clicked();
    void on_up_sec_clicked();
    void on_down_sec_clicked();
    void on_pb_ok_clicked();

    void on_pb_cancel_clicked();

private:
    Ui::timeSetup *ui;
    void keyPressEvent(QKeyEvent *event);
    void initDisplay();

};

#endif // TIMESETUP_H
