#ifndef VNC_REMOTELOGIN_H
#define VNC_REMOTELOGIN_H

#include <QDialog>

namespace Ui {
class vnc_RemoteLogin;
}

class vnc_RemoteLogin : public QDialog
{
    Q_OBJECT

public:
    explicit vnc_RemoteLogin(QWidget *parent = 0);
    ~vnc_RemoteLogin();

private slots:
    void on_pb_connect_clicked();
    void connectStatusChange(qint32 pStatus);
private:
    Ui::vnc_RemoteLogin *ui;

signals:
    void commuStatus(qint32 pStatus);
};

#endif // VNC_REMOTELOGIN_H
