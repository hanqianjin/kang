#ifndef WIFICONNECT_H
#define WIFICONNECT_H

#include <QDialog>
#include "wireless.h"
#include "plugin/pltkeyboard.h"
#include <QTimer>
namespace Ui {
class WifiConnect;
}

class WifiConnect : public QDialog
{
    Q_OBJECT

public:

    explicit WifiConnect(SSIDInfo* Info, pltKeyBoard* keyBoard, QWidget *parent = 0);
    ~WifiConnect();
    qint32 exec();
private slots:
    void on_pb_pair_clicked();
    void on_pb_cancel_clicked();
    void on_pb_pwView_clicked(bool checked);

    void on_passWordEdit_clicked();

    void on_passWordEdit_loseFocus();
    void on_timeout();
private:
    void initDisplay();

private:
    Ui::WifiConnect *ui;
    SSIDInfo* pWifiInfo;
    qint32 netFd;
    pltKeyBoard *pKeyBoard;
    QTimer *mTimer;
    qint32 timeflag;
};

#endif // WIFICONNECT_H
