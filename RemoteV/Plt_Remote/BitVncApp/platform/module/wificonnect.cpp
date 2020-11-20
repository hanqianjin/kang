#include "wificonnect.h"
#include "ui_wificonnect.h"

WifiConnect::WifiConnect(SSIDInfo *Info, pltKeyBoard* keyBoard, QWidget *parent) :
    pKeyBoard(keyBoard),
    QDialog(parent),
    pWifiInfo(Info),
    ui(new Ui::WifiConnect)
{
    ui->setupUi(this);
    initDisplay();
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::WindowModal);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    netFd = -1;
}

WifiConnect::~WifiConnect()
{
    delete ui;
}


void WifiConnect::on_pb_pair_clicked()
{
    char * passwd = ui->passWordEdit->text().toUtf8().data();
    char *ssid = pWifiInfo->ssid;

    qint32 res = wireless_connect(&netFd, ssid, passwd);
    if(res == 0)
    {
        this->close();
    }else
    {
        ui->lblWarning->setVisible(true);
    }
    return;
}
qint32 WifiConnect::exec()
{
    pKeyBoard->show();
    ui->passWordEdit->setFocus();
    QDialog::exec();
    pKeyBoard->hide();
    return netFd;
}
void WifiConnect::on_pb_cancel_clicked()
{
    this->close();
}

void WifiConnect::initDisplay()
{
    QString strNotice = QString("Wi-fi network “ %1 ” need to enter password.").arg(pWifiInfo->ssid);
    ui->lblnotice->setText(strNotice);

    ui->lblWarning->setVisible(false);
}

void WifiConnect::on_pb_pwView_clicked(bool checked)
{
    if(checked)
    {
        ui->passWordEdit->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->passWordEdit->setEchoMode(QLineEdit::Password);
    }
}

void WifiConnect::on_passWordEdit_clicked()
{
    pKeyBoard->show();
}


void WifiConnect::on_passWordEdit_loseFocus()
{
    pKeyBoard->hide();
    close();
}
