#ifndef STATEBOX_H
#define STATEBOX_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class StateBox;
}

class StateBox : public QWidget
{
    Q_OBJECT

public:
    explicit StateBox(QWidget *parent = 0);
    ~StateBox();
    void showMessage(QString info, bool autoClose = false, int time = 2000);

signals:
    void stateboxClosed();

protected:
    void closeEvent(QCloseEvent *e);

private:
    void delayClose(bool autoClose, int time);

private:
    Ui::StateBox *ui;
    QTimer *m_timer;
};

#endif // STATEBOX_H
