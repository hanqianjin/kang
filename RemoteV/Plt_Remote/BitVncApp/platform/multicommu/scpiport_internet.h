#ifndef SCPIPORT_INTERNET_H
#define SCPIPORT_INTERNET_H

#include "scpiport.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QSettings>
#include <QByteArray>
#include <QDateTime>

#ifdef Q_OS_LINUX
#include <netinet/tcp.h>
#endif

#define SETTING_TCPSERVER_PORT  "SYS/NETWORK/TCPSERVERPORT"

class ScpiPort_internet : public ScpiPort_common
{
    Q_OBJECT
public:
    ScpiPort_internet(qint32 *port = NULL,QObject *parent = 0);
    explicit ScpiPort_internet(QObject *parent = 0);
    void * getUserContext(){
        return (void *)m_tcpSocketConnected;
    }
    void closeConn();    
    void lostConn();

    void closeBitConn();
    void buildBitConn();
private:
    int set_tcp_keepAlive(int fd, int start, int interval, int count);

public slots:
    void slotAcceptConnection();
    void slotReadTCPConnected();
    void slotCloseTCPConnection();  

private:
    QTcpSocket *m_tcpSocketConnected;
    QSettings   m_setting;
    qint32     *m_port;
    QTcpServer  m_tcpServer;
    QByteArray  m_cmdBuffer;
};

#endif // SCPIPORT_INTERNET_H
