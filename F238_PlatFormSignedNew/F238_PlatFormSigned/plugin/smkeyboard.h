#ifndef SMKEYBOARD_H
#define SMKEYBOARD_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class SmKeyBoard;
}

class SmKeyBoard : public QWidget
{
    Q_OBJECT

public:
    explicit SmKeyBoard(QWidget *parent = 0);
    ~SmKeyBoard();
    void setTitle(QString str);
private slots:
    void on_pb_cancel_clicked();
    void btn_clicked();

private:
    void initMap();
private:
    QMap <QPushButton*,qint32> *key_btn;
    Ui::SmKeyBoard *ui;
};

#endif // SMKEYBOARD_H
