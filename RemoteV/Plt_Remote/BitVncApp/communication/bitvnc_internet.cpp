#include "bitvnc_internet.h"

bitvnc_internet* bitvnc_internet::m_pInstance = 0;
QMutex bitvnc_internet::m_Mutex;
pthread_mutex_t Vnc_CommuLock;
extern pthread_mutex_t SA_lockobj;

bitvnc_internet::bitvnc_internet(QObject *parent):
    QObject(parent),
    pStart(0),
    pEnd(0),
    dataComplete(1),
    transFileFlag(0),
    m_LocalSocketConnected(NULL)
{
    socket = new QTcpSocket();

    //连接信号和槽   （发送者，信号，接收者，槽）
    QObject::connect(socket, &QTcpSocket::readyRead, this, &bitvnc_internet::tcp_socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &bitvnc_internet::tcp_socket_Disconnected);

    server = new QLocalServer(this);
    server->removeServer("IPCServer");
    server->listen("IPCServer");
    connect(server, &QLocalServer::newConnection, this, &bitvnc_internet::slotAcceptConnection);
    memset(gOriginalMeasureVal,0,sizeof(qreal)*801);

    pDataHandle = new bitvnc_DataHandling(this);
}

bitvnc_internet::~bitvnc_internet()
{
    if(!!m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = 0;
    }
}

QTcpSocket *bitvnc_internet::GetTcpSocket()
{
    return socket;
}

QLocalServer *bitvnc_internet::GetLocalServer()
{
    return server;
}

qint32 bitvnc_internet::SetInternetConnect(QString pIP, qint32 pPort)
{
    //注销已有连接
    socket->abort();

    //连接服务器
    socket->connectToHost(pIP, pPort);

    //等待连接成功
    if(!socket->waitForConnected(3000000))
    {
        pConnectStatus = 0;
        emit ConnectStatus(pConnectStatus);
        return false;
    }
    pConnectStatus = 1;
    emit ConnectStatus(pConnectStatus);
    return true;
}

qint32 bitvnc_internet::SetInternetDisconnect()
{
    //断开连接
    socket->disconnectFromHost();
    pConnectStatus = 0;
    emit ConnectStatus(pConnectStatus);
    return true;
}

void bitvnc_internet::tcp_socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据

    buffer = socket->readAll();
    ProcessingData(&buffer);
    //pDataHandle->readData(buffer);
    //pDataHandle->readOneInfo(&tmpBuffer);
//    emit readData(buffer);
}

void bitvnc_internet::tcp_socket_Disconnected()
{
    pConnectStatus = 0;
    emit ConnectStatus(pConnectStatus);
    return;
}

qint32 bitvnc_internet::GetInternetStatus()
{
    return pConnectStatus;;
}

void bitvnc_internet::slotAcceptConnection()
{


}

bitvnc_internet* bitvnc_internet::GetInstance()
{
    if(0 == m_pInstance)
    {
        QMutexLocker mutexLocker(&m_Mutex);
        if(0 == m_pInstance)
            m_pInstance = new bitvnc_internet();
    }
    return m_pInstance;
}

void bitvnc_internet::saveOriData(QByteArray *buffer)
{
    memcpy(gOriginalMeasureVal,(*buffer),sizeof(qreal)*801);

/*
    pEnd = (pEnd == 9) ? 0 : pEnd + 1;
    if(pEnd == pStart)
    {
        pStart = (pStart == 9) ? 0 : pStart + 1;
    }
    memcpy(gOriginalMeasureVal[pStart],(*buffer),sizeof(qreal)*801);
*/
    return;
}

qreal* bitvnc_internet::getOriData()
{
    qreal* data;
    data = gOriginalMeasureVal;
    /*
    if(pStart + 1 == pEnd)
    {
        data = 0;
    }else
    {
        data = gOriginalMeasureVal[pStart];
        pStart = (pStart == 9) ? 0 : pStart + 1;
    }
    */
    return data;
}


void bitvnc_internet::ProcessingData(QByteArray* buffer)
{
    qint32 len = buffer->size();
    QString strTail = "\r\n";
    qint32 iback = 0;
    if(!dataComplete)//上一次数据需要和本次数据合并
    {
        buffer->insert(0,tmpData);
        tmpData.clear();
    }

    while(true)
    {
        iback = buffer->indexOf(strTail,0);
        if(iback < 0)
        {
            break;
        }
        if(transFileFlag) TransFile(buffer->left(iback));

        if(iback == 6408)//if iback is 6408 raw data
        {
//          pthread_mutex_lock(&SA_lockobj);
            saveOriData(buffer);
//          pthread_mutex_unlock(&SA_lockobj);
        }
        isTransFile(buffer->left(iback));
        buffer->remove(0,iback+2);
    }


    len = buffer->size();
    if(!len) //0 is complete
    {
        dataComplete = 1;
    }else
    {
        tmpData.append(*buffer);
        dataComplete = 0;
    }
    return;
}

//Determine whether it is file transfer
bool bitvnc_internet::isTransFile(QByteArray buffer)
{
    QString data = QString(buffer);
    if(!(data.contains("File Ready."))) return false;
    transFileFlag = 1;
    QStringList listCmd = data.split(".");
    strFileSize = (QString)listCmd.at(1);
    strFile     = (QString)listCmd.at(2);
    //strFile.remove("\r\n");
    return true;
}

#include <QMessageBox>
void bitvnc_internet::TransFile(QByteArray buffer)
{
    transFileFlag = 0;
    if(buffer.size() != strFileSize.toInt()) return;
#if 0 //check when send command
    QFileInfo info(strFile);
    QDir dir;
    if (!info.exists())
    {
        if (!dir.mkpath(info.path()))
        {
            return;
        }
    }
#endif
    QFile file(strFile);

    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        return;
    }
    file.write(buffer,strFileSize.toInt());
    file.close();
    emit fileReceive();
    return ;
}
