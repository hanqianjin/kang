#include "vnc_remotelogin.h"
#include "ui_vnc_remotelogin.h"
#include "bitvnchandle.h"
#include "../platform/remoteinterface.h"
vnc_RemoteLogin::vnc_RemoteLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vnc_RemoteLogin)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog);

    connect(BitVncHandle::GetVncInternetHandle(),SIGNAL(ConnectStatus(qint32)),this,SLOT(connectStatusChange(qint32)));

}

vnc_RemoteLogin::~vnc_RemoteLogin()
{
    delete ui;
}

void vnc_RemoteLogin::on_pb_connect_clicked()
{
    //根据不同模式调用不同模式的连接接口
    if(BitVncHandle::GetVncInternetHandle()->GetInternetStatus())
    {
        BitVncHandle::GetVncInternetHandle()->SetInternetDisconnect();
    }
    else
    {
        //init
        QString pIP = ui->IP_Edit->text();
        qint32  pPort = ui->Port_Edit->text().toInt();
        if(BitVncHandle::GetVncInternetHandle()->SetInternetConnect(pIP,pPort))
        {
            //set
            QString strCmd = ":SYSTem:PRESet\n";
            BitVncHandle::GetVncInternetHandle()->GetTcpSocket()->write(strCmd.toLatin1());

            remoteinterface::getsaremotehandle()->pcontrolInterface->PresetDefaultStates();
            this->close();
        }
    }
}

void vnc_RemoteLogin::connectStatusChange(qint32 pStatus)
{
    emit commuStatus(pStatus);
    return;
}
