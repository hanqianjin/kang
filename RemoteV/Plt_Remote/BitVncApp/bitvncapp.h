#ifndef BITVNCAPP_H
#define BITVNCAPP_H

#include <QMainWindow>
class QPushButton;
class BitPlatForm;
class vnc_RemoteLogin;
class vnc_threadrefresh;
namespace Ui {
class BitVncApp;
}

class BitVncApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit BitVncApp(QWidget *parent = 0);
    ~BitVncApp();
    void GetRemotePara();
protected slots:
    void refreshUI();
private slots:
    void on_notice();
    void connect_clicked();
    void commuStatusChange(qint32 pStatus);
private:
    void initPointer();
private:
    Ui::BitVncApp *ui;

    BitPlatForm *pBitPlat;
    vnc_RemoteLogin *commu;

    vnc_threadrefresh *mThread;
    QPushButton* pCommuStatus;
};

#endif // BITVNCAPP_H
