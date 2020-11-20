#include "localcommunicate.h"

#include <QDebug>

LocalCommunicate *LocalCommunicate::instance()
{
    static LocalCommunicate data;
    return &data;
}

LocalCommunicate::LocalCommunicate(QObject *parent) :
    QLocalSocket(parent)
{
    abort();//Johnson 0118 abort the current connecting
    setServerName(LOCALSERVER);
    connectToServer(QIODevice::ReadWrite);
}

bool LocalCommunicate::changeMode(ScpiMode mode)
{
    //****Johnson 190128
    switch(mode)
    {
    case Mode_remote_internet:
        this->write("Remote internet");
        break;
    case Mode_remote_gpib:
        this->write("Rmote gpib");
        break;
    case Mode_remote_uart:
        this->write("Remote uart");
        break;
    case Mode_remote_usb:
        this->write("Remote usb");
        break;
    default: break;
    }

    //wait..
    if (!this->waitForBytesWritten(TIMEOUT))
        return false;

    if (!this->waitForReadyRead(TIMEOUT))
        return false;

    //Data read from GUI Process
    QByteArray buffer = this->readAll();
    qDebug()<<buffer;

    return true;
}
