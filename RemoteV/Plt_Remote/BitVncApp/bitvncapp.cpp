#include "bitvncapp.h"
#include "ui_bitvncapp.h"
#include "bitplatform.h"
#include "vnc_remotelogin.h"
#include "bitvnchandle.h"
#include "bitvnc_internet.h"
#include "vnc_threadrefresh.h"
#include "platform/remoteinterface.h"
#include <QLibrary>
#include <QMessageBox>
BitVncApp::BitVncApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BitVncApp)
{
    ui->setupUi(this);

    initPointer();

    commu = new vnc_RemoteLogin(this);
    connect(commu,SIGNAL(commuStatus(qint32)),this,SLOT(commuStatusChange(qint32)));
    pCommuStatus = new QPushButton();
    connect(pCommuStatus,SIGNAL(clicked()),this,SLOT(connect_clicked()));
    pCommuStatus->setText("disconnection");
    ui->statusBar->addWidget(pCommuStatus,1000);

    mThread = new vnc_threadrefresh(this);
    connect(mThread,SIGNAL(refresh()),this,SLOT(refreshUI()));
    mThread->start();
    //connect(BitVncHandle::GetVncInternetHandle(),SIGNAL(fileReceive()),this,SLOT(on_notice()));
    //bitsa->setGeometry(0,0,1280,800);
}

BitVncApp::~BitVncApp()
{
    delete ui;
}

void BitVncApp::refreshUI()
{
    remoteinterface::getsaremotehandle()->graphRefreshFunc();
    /*BitVncHandle::GetVncAppHandle()->pSaAna->graphRefreshFunc()*/;
    repaint();

    QString strCmd = ":TRACe:DATA:RAWData?\n";
    BitVncHandle::GetVncInternetHandle()->GetTcpSocket()->write(strCmd.toLatin1());
}
void BitVncApp::initPointer()
{
    //Handle of app
    pBitPlat = new BitPlatForm(this);
    BitVncHandle::SetVncAppHandle(pBitPlat);

    BitVncHandle::SetVncInternetHandle(bitvnc_internet::GetInstance());

    pBitPlat->show();

}

void BitVncApp::GetRemotePara()
{

}


void BitVncApp::connect_clicked()
{
    commu->exec();
}

void BitVncApp::commuStatusChange(qint32 pStatus)
{
    if(pStatus)
    {
        pCommuStatus->setText("connection");
    }else
    {
        pCommuStatus->setText("disconnection");
    }
}

void BitVncApp::on_notice()
{
     QMessageBox::information(pBitPlat, "Notice", "File receive successfully!");
}
